use super::LunarWindow;
use super::LunarVkBackend;

pub struct LunarHAL {
    pub backend: LunarVkBackend::LunarVk::LVKBackend,
}

impl LunarHAL {
    pub fn initialize_lunar_graphics(window: &winit::Window) -> Self {
        let mut backend = LunarVkBackend::LunarVk::LVKBackend::create_backend(&window);

        Self {
            backend,
        }
    }

    pub fn draw_frame(&mut self) {
        self.backend.draw_frame();
    }
}