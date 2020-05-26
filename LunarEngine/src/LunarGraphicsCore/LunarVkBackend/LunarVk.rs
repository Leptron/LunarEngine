use super::LunarVkDevice;

pub struct LVKBackend {
    lvk_device: LunarVkDevice::LunarVkDevice,
}

impl LVKBackend {
    pub fn create_backend(window: &winit::Window) -> Self {
        let mut lvk_device = LunarVkDevice::LunarVkDevice::init_vk(&window);

        Self {
            lvk_device,
        }
    }

    pub fn draw_frame(&mut self) {
        //drawing code
    }
}