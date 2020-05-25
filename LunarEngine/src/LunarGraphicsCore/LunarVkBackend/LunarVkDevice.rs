use ash::version::EntryV1_0;
use ash::version::InstanceV1_0;
use ash::vk;
use std::ffi::{CStr, CString};
use std::os::raw::c_void;
use std::ptr;
use ash::vk_make_version;
use ash::version::DeviceV1_0;

#[cfg(target_os = "windows")]
use ash::extensions::khr::Win32Surface;
#[cfg(all(unix, not(target_os = "android"), not(target_os = "macos")))]
use ash::extensions::khr::XlibSurface;
#[cfg(target_os = "macos")]
use ash::extensions::mvk::MacOSSurface;

use ash::extensions::ext::DebugUtils;
use ash::extensions::khr::Surface;
use ash::{vk_version_major, vk_version_minor, vk_version_patch};
use std::os::raw::c_char;

#[cfg(target_os = "macos")]
use cocoa::appkit::{NSView, NSWindow};
#[cfg(target_os = "macos")]
use cocoa::base::id as cocoa_id;
#[cfg(target_os = "macos")]
use metal::CoreAnimationLayer;
#[cfg(target_os = "macos")]
use objc::runtime::YES;

use super::LunarVkUtilityTools;

struct QueueFamilyIndices {
    graphics_family: Option<u32>,
}

impl QueueFamilyIndices {
    pub fn is_complete(&self) -> bool {
        self.graphics_family.is_some()
    }
}

struct ValidationInfo {
    pub is_enable: bool,
    pub required_validation_layers: [&'static str; 1],
}

pub struct LunarVkDevice {
    _entry: ash::Entry,
    instance: ash::Instance,
    validation: ValidationInfo,
    debug_utils_loader: ash::extensions::ext::DebugUtils,
    debug_merssager: vk::DebugUtilsMessengerEXT,
    _physical_device: vk::PhysicalDevice,
    device: ash::Device,
    _graphics_queue: vk::Queue,
}

impl LunarVkDevice {
    pub fn init_vk() -> Self {
        let validation = ValidationInfo{
            is_enable: true,
            required_validation_layers: ["VK_LAYER_KHRONOS_validation"],
        };

        let entry = ash::Entry::new().unwrap();
        let instance = LunarVkDevice::create_instance(&entry, &validation);
        let (debug_utils_loader, debug_merssager) = LunarVkDevice::setup_debug_utils(&validation, &entry, &instance);
        let physical_device = LunarVkDevice::pick_physical_device(&instance);
        let (logical_device, graphics_queue) =
            LunarVkDevice::create_logical_device(&instance, physical_device, &validation);

        Self {
            _entry: entry,
            instance,
            validation,
            debug_utils_loader,
            debug_merssager,
            _physical_device: physical_device,
            device: logical_device,
            _graphics_queue: graphics_queue,
        }
    }

    #[cfg(target_os = "macos")]
    fn required_extension_names() -> Vec<*const i8> {
        vec![
            Surface::name().as_ptr(),
            MacOSSurface::name().as_ptr(),
            DebugUtils::name().as_ptr(),
        ]
    }

    #[cfg(all(windows))]
    fn required_extension_names() -> Vec<*const i8> {
        vec![
            Surface::name().as_ptr(),
            Win32Surface::name().as_ptr(),
            DebugUtils::name().as_ptr(),
        ]
    }

    #[cfg(all(unix, not(target_os = "android"), not(target_os = "macos")))]
    fn required_extension_names() -> Vec<*const i8> {
        vec![
            Surface::name().as_ptr(),
            XlibSurface::name().as_ptr(),
            DebugUtils::name().as_ptr(),
        ]
    }
    fn create_instance(entry: &ash::Entry, validation: &ValidationInfo,) -> ash::Instance {
        if validation.is_enable && LunarVkDevice::check_validation_layer_support(validation, entry) == false {
            panic!("Validation layers requested, but not available!");
        }
        
        let app_name = CString::new("LunarEngine").unwrap();
        let engine_name = CString::new("Lunar Engine").unwrap();
        let app_info = vk::ApplicationInfo {
            s_type: vk::StructureType::APPLICATION_INFO,
            p_next: ptr::null(),
            p_application_name: app_name.as_ptr(),
            application_version: vk_make_version!(1, 0, 0),
            p_engine_name: engine_name.as_ptr(),
            engine_version: vk_make_version!(1, 0, 0),
            api_version: vk_make_version!(1, 0, 92),
        };

        let debug_utils_create_info = LunarVkDevice::populate_debug_messenger_create_info();
        let extension_names = LunarVkDevice::required_extension_names();

        let requred_validation_layer_raw_names: Vec<CString> = validation
            .required_validation_layers
            .iter()
            .map(|layer_name| CString::new(*layer_name).unwrap())
            .collect();

        let enable_layer_names: Vec<*const i8> = requred_validation_layer_raw_names
            .iter()
            .map(|layer_name| layer_name.as_ptr())
            .collect();

        let create_info = vk::InstanceCreateInfo {
            s_type: vk::StructureType::INSTANCE_CREATE_INFO,
            p_next: if validation.is_enable {
                &debug_utils_create_info as *const vk::DebugUtilsMessengerCreateInfoEXT
                    as *const c_void
            } else {
                ptr::null()
            },
            flags: vk::InstanceCreateFlags::empty(),
            p_application_info: &app_info,
            pp_enabled_layer_names: if validation.is_enable {
                enable_layer_names.as_ptr()
            } else {
                ptr::null()
            },
            enabled_layer_count: if validation.is_enable {
                enable_layer_names.len()
            } else {
                0
            } as u32,
            pp_enabled_extension_names: extension_names.as_ptr(),
            enabled_extension_count: extension_names.len() as u32,
        };

        let instance: ash::Instance = unsafe {
            entry
                .create_instance(&create_info, None).expect("Failed to create instance!")
        };

        instance
    }

    fn check_validation_layer_support(validation: &ValidationInfo, entry: &ash::Entry) -> bool {
        let layer_properties = entry
            .enumerate_instance_layer_properties()
            .expect("failed to enumerate Instance layer properties");

        if layer_properties.len() <= 0 {
            eprintln!("No available layers!");
            return false;
        } else {
            println!("Instance available layers : ");
            for layer in layer_properties.iter() {
                let layer_name = LunarVkUtilityTools::vk_to_string(&layer.layer_name);
                println!("\t{}", layer_name);
            }
        }

        for required_layer_name in validation.required_validation_layers.iter() {
            let mut is_layerFound = false;

            for layer_property in layer_properties.iter() {
                let test_name = LunarVkUtilityTools::vk_to_string(&layer_property.layer_name);
                if(*required_layer_name) == test_name {
                    is_layerFound = true;
                    break;
                }
            }

            if is_layerFound == false {
                return false;
            }
        }

        true
    }

    fn populate_debug_messenger_create_info() -> vk::DebugUtilsMessengerCreateInfoEXT {
        vk::DebugUtilsMessengerCreateInfoEXT {
            s_type: vk::StructureType::DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            p_next: ptr::null(),
            flags: vk::DebugUtilsMessengerCreateFlagsEXT::empty(),
            message_severity: vk::DebugUtilsMessageSeverityFlagsEXT::WARNING |
                // vk::DebugUtilsMessageSeverityFlagsEXT::VERBOSE |
                // vk::DebugUtilsMessageSeverityFlagsEXT::INFO |
                vk::DebugUtilsMessageSeverityFlagsEXT::ERROR,
            message_type: vk::DebugUtilsMessageTypeFlagsEXT::GENERAL
                | vk::DebugUtilsMessageTypeFlagsEXT::PERFORMANCE
                | vk::DebugUtilsMessageTypeFlagsEXT::VALIDATION,
            pfn_user_callback: Some(LunarVkDevice::vulkan_debug_utils_callback),
            p_user_data: ptr::null_mut(),
        }
    }

    fn setup_debug_utils(validation_in: &ValidationInfo, entry: &ash::Entry, instance: &ash::Instance) -> (ash::extensions::ext::DebugUtils, vk::DebugUtilsMessengerEXT) {
        let debug_utils_loader = ash::extensions::ext::DebugUtils::new(entry, instance);

        if validation_in.is_enable == false {
            (debug_utils_loader, ash::vk::DebugUtilsMessengerEXT::null())
        } else {
            let messenger_ci = LunarVkDevice::populate_debug_messenger_create_info();
            let utils_messenger = unsafe {
                debug_utils_loader
                    .create_debug_utils_messenger(&messenger_ci, None)
                    .expect("Debug Utils Callback")
            };

            (debug_utils_loader, utils_messenger)
        }
    }

    unsafe extern "system" fn vulkan_debug_utils_callback(
        message_severity: vk::DebugUtilsMessageSeverityFlagsEXT,
        message_type: vk::DebugUtilsMessageTypeFlagsEXT,
        p_callback_data: *const vk::DebugUtilsMessengerCallbackDataEXT,
        _p_user_data: *mut c_void,
    ) -> vk::Bool32 {
        let severity = match message_severity {
            vk::DebugUtilsMessageSeverityFlagsEXT::VERBOSE => "[Verbose]",
            vk::DebugUtilsMessageSeverityFlagsEXT::WARNING => "[Warning]",
            vk::DebugUtilsMessageSeverityFlagsEXT::ERROR => "[Error]",
            vk::DebugUtilsMessageSeverityFlagsEXT::INFO => "[Info]",
            _ => "[Unknown]",
        };
        let types = match message_type {
            vk::DebugUtilsMessageTypeFlagsEXT::GENERAL => "[General]",
            vk::DebugUtilsMessageTypeFlagsEXT::PERFORMANCE => "[Performance]",
            vk::DebugUtilsMessageTypeFlagsEXT::VALIDATION => "[Validation]",
            _ => "[Unknown]",
        };
        let message = CStr::from_ptr((*p_callback_data).p_message);
        println!("[Debug]{}{}{:?}", severity, types, message);
    
        vk::FALSE
    }

    fn pick_physical_device(instance: &ash::Instance) -> vk::PhysicalDevice {
        let physical_devices = unsafe {
            instance
                .enumerate_physical_devices()
                .expect("Failed to enumerate Physical Devices!")
        };

        println!("{} devices (GPU) found with vulkan support.", physical_devices.len());

        let mut result = None;
        for &physical_device in physical_devices.iter() {
            if LunarVkDevice::is_physical_device_suitable(instance, physical_device) {
                if result.is_none() {
                    result = Some(physical_device)
                }
            }
        }

        match result {
            None => panic!("Failed to find a suitable GPU!"),
            Some(physical_device) => physical_device,
        }
    }

    fn is_physical_device_suitable(instance: &ash::Instance, physical_device: vk::PhysicalDevice) -> bool {
        let device_properties = unsafe { instance.get_physical_device_properties(physical_device) };
        let device_features = unsafe { instance.get_physical_device_features(physical_device) };
        let device_queue_families =
            unsafe { instance.get_physical_device_queue_family_properties(physical_device) };

        let device_type = match device_properties.device_type {
            vk::PhysicalDeviceType::CPU => "Cpu",
            vk::PhysicalDeviceType::INTEGRATED_GPU => "Integrated GPU",
            vk::PhysicalDeviceType::DISCRETE_GPU => "Discrete GPU",
            vk::PhysicalDeviceType::VIRTUAL_GPU => "Virtual GPU",
            vk::PhysicalDeviceType::OTHER => "Unknown",
            _ => panic!(),
        };

        let device_name = LunarVkUtilityTools::vk_to_string(&device_properties.device_name);
        println!(
            "\tDevice Name: {}, id: {}, type: {}",
            device_name, device_properties.device_id, device_type
        );

        let major_version = vk_version_major!(device_properties.api_version);
        let minor_version = vk_version_minor!(device_properties.api_version);
        let patch_version = vk_version_patch!(device_properties.api_version);

        for queue_family in device_queue_families.iter() {
            let is_graphics_support = if queue_family.queue_flags.contains(vk::QueueFlags::GRAPHICS)
            {
                "support"
            } else {
                "unsupport"
            };
            let is_compute_support = if queue_family.queue_flags.contains(vk::QueueFlags::COMPUTE) {
                "support"
            } else {
                "unsupport"
            };
            let is_transfer_support = if queue_family.queue_flags.contains(vk::QueueFlags::TRANSFER)
            {
                "support"
            } else {
                "unsupport"
            };
            let is_sparse_support = if queue_family
                .queue_flags
                .contains(vk::QueueFlags::SPARSE_BINDING)
            {
                "support"
            } else {
                "unsupport"
            };
        }

        let indices = LunarVkDevice::find_queue_family(instance, physical_device);

        return indices.is_complete();
    }

    fn find_queue_family(instance: &ash::Instance, physical_device: vk::PhysicalDevice,) -> QueueFamilyIndices {
        let queue_families =
            unsafe { instance.get_physical_device_queue_family_properties(physical_device) };

        let mut queue_family_indicies = QueueFamilyIndices {
            graphics_family: None,
        };

        let mut index = 0;
        for queue_family in queue_families.iter() {
            if queue_family.queue_count > 0
                && queue_family.queue_flags.contains(vk::QueueFlags::GRAPHICS)
            {
                queue_family_indicies.graphics_family = Some(index);
            }

            if queue_family_indicies.is_complete() {
                break;
            }

            index += 1;
        }

        queue_family_indicies
    }

    fn create_logical_device(instance: &ash::Instance, physical_device: vk::PhysicalDevice, validation: &ValidationInfo) -> (ash::Device, vk::Queue) {
        let indicies = LunarVkDevice::find_queue_family(instance, physical_device);

        let queue_priorities = [1.0_f32];
        let queue_create_info = vk::DeviceQueueCreateInfo  {
            s_type: vk::StructureType::DEVICE_QUEUE_CREATE_INFO,
            p_next: ptr::null(),
            flags: vk::DeviceQueueCreateFlags::empty(),
            queue_family_index: indicies.graphics_family.unwrap(),
            p_queue_priorities: queue_priorities.as_ptr(),
            queue_count: queue_priorities.len() as u32,
        };

        let physical_device_features = vk::PhysicalDeviceFeatures {
            ..Default::default()
        };

        let requred_validation_layer_raw_names: Vec<CString> = validation
            .required_validation_layers
            .iter()
            .map(|layer_name| CString::new(*layer_name).unwrap())
            .collect();
        let enable_layer_names: Vec<*const c_char> = requred_validation_layer_raw_names
            .iter()
            .map(|layer_name| layer_name.as_ptr())
            .collect();

        let device_create_info = vk::DeviceCreateInfo {
            s_type: vk::StructureType::DEVICE_CREATE_INFO,
            p_next: ptr::null(),
            flags: vk::DeviceCreateFlags::empty(),
            queue_create_info_count: 1,
            p_queue_create_infos: &queue_create_info,
            enabled_layer_count: if validation.is_enable {
                enable_layer_names.len()
            } else {
                0
            } as u32,
            pp_enabled_layer_names: if validation.is_enable {
                enable_layer_names.as_ptr()
            } else {
                ptr::null()
            },
            enabled_extension_count: 0,
            pp_enabled_extension_names: ptr::null(),
            p_enabled_features: &physical_device_features,
        };

        let device: ash::Device = unsafe {
            instance
                .create_device(physical_device, &device_create_info, None)
                .expect("Failed to create logical device")
        };

        let graphics_queue = unsafe { device.get_device_queue(indicies.graphics_family.unwrap(), 0) };

        (device, graphics_queue)
    }
}

impl Drop for LunarVkDevice {
    fn drop(&mut self) {
        unsafe {
            self.device.destroy_device(None);
            if(self.validation.is_enable) {
                self.debug_utils_loader.destroy_debug_utils_messenger(self.debug_merssager, None);
            }
            self.instance.destroy_instance(None);
        }
    }
}