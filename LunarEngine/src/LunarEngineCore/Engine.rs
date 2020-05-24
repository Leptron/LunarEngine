use super::super::LunarGraphicsCore;

use winit:: {
    Event, WindowEvent,
};

pub struct LunarEngine {
    lWindow: LunarGraphicsCore::LunarWindow::LunarWindow,
}

impl LunarEngine {
    pub fn init_engine() -> Self {
        let mut lWindow = LunarGraphicsCore::LunarWindow::LunarWindow::default();
        Self {
            lWindow,
        }
    }

    pub fn init_graphics() {
    }

    pub fn render_loop(&mut self) {
        let mut running = true;
        while running {
            self.lWindow.events_loop.poll_events(|event| match event {
                Event::WindowEvent {
                    event: WindowEvent::CloseRequested,
                    ..
                } => running = false,
                _ => (),
            });
        }
    }
}
