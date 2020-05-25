use super::LunarVkDevice;

pub struct LVKBackend {
    lvk_device: LunarVkDevice::LunarVkDevice,
}

impl LVKBackend {
    pub fn create_backend() -> Self {
        let mut lvk_device = LunarVkDevice::LunarVkDevice::init_vk();

        Self {
            lvk_device,
        }
    }

    pub fn draw_frame(&mut self) {
        //drawing code
    }
}