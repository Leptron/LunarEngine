use ash::version::EntryV1_0;
use ash::version::InstanceV1_0;
use ash::vk;
use std::ffi::CString;
use std::ptr;
use ash::vk_make_version;

#[cfg(target_os = "windows")]
use ash::extensions::khr::Win32Surface;
#[cfg(all(unix, not(target_os = "android"), not(target_os = "macos")))]
use ash::extensions::khr::XlibSurface;
#[cfg(target_os = "macos")]
use ash::extensions::mvk::MacOSSurface;

use ash::extensions::ext::DebugUtils;
use ash::extensions::khr::Surface;

#[cfg(target_os = "macos")]
use cocoa::appkit::{NSView, NSWindow};
#[cfg(target_os = "macos")]
use cocoa::base::id as cocoa_id;
#[cfg(target_os = "macos")]
use metal::CoreAnimationLayer;
#[cfg(target_os = "macos")]
use objc::runtime::YES;


pub struct LunarVkDevice {
    _entry: ash::Entry,
    instance: ash::Instance,
}

impl LunarVkDevice {
    pub fn init_vk() -> Self {
        let entry = ash::Entry::new().unwrap();
        let instance = LunarVkDevice::create_instance(&entry);

        Self {
            _entry: entry,
            instance,
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
    fn create_instance(entry: &ash::Entry) -> ash::Instance {
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

        let extension_names = LunarVkDevice::required_extension_names();

        let create_info = vk::InstanceCreateInfo {
            s_type: vk::StructureType::INSTANCE_CREATE_INFO,
            p_next: ptr::null(),
            flags: vk::InstanceCreateFlags::empty(),
            p_application_info: &app_info,
            pp_enabled_layer_names: ptr::null(),
            enabled_layer_count: 0,
            pp_enabled_extension_names: extension_names.as_ptr(),
            enabled_extension_count: extension_names.len() as u32,
        };

        let instance: ash::Instance = unsafe {
            entry
                .create_instance(&create_info, None).expect("Failed to create instance!")
        };

        instance
    }
}

impl Drop for LunarVkDevice {
    fn drop(&mut self) {
        unsafe {
            self.instance.destroy_instance(None);
        }
    }
}