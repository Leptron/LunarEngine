use super::super::LunarGraphicsCore;
use winit::{Event, VirtualKeyCode, ElementState, KeyboardInput, WindowEvent, EventsLoop};

pub struct LunarEngine {
    lWindow: LunarGraphicsCore::LunarWindow::LunarWindow,
    pub lHAL: LunarGraphicsCore::LunarGFX::LunarHAL,
}

impl LunarEngine {
    pub fn init_engine() -> Self {
        let lWindow = LunarGraphicsCore::LunarWindow::LunarWindow::default();
        let lHAL = LunarGraphicsCore::LunarGFX::LunarHAL::initialize_lunar_graphics();

        Self {
            lWindow: lWindow,
            lHAL,
        }
    }

    pub fn poll_events_loop(events_loop: &mut EventsLoop) -> String {
        let mut output = String::from("render");
        events_loop.poll_events(|event| match event {
            Event::WindowEvent {
                event: WindowEvent::CloseRequested,
                ..
            } => output = String::from("close"),
            _ => (),
        });
        output
    }

    pub fn return_HAL(self) -> LunarGraphicsCore::LunarGFX::LunarHAL {
        return self.lHAL;
    }

    pub fn render_loop(&mut self) {
       loop {
           let input_conditions = LunarEngine::poll_events_loop(&mut self.lWindow.events_loop);
           if input_conditions == String::from("close") {
               break;
           }

           self.lHAL.draw_frame();
       }
    }
}
