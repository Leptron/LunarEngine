use winit::{
    dpi::LogicalSize, CreationError, Event, EventsLoop, Window, WindowBuilder, WindowEvent,
};
use std::clone;

pub struct LunarWindow {
    pub events_loop: EventsLoop,
    pub window: Window,
}

fn duplicate<T>(x: T) -> T { x }

impl LunarWindow {
    pub fn new(title: String, width: f64, height: f64,) -> Self {
        let events_loop = EventsLoop::new();
        let window = WindowBuilder::new()
            .with_title(title)
            .with_dimensions(LogicalSize{
                width, height,
            })
            .build(&events_loop)
            .expect("Failed to build window");
        
        Self {
            events_loop,
            window,
        }
    }
}

impl Default for LunarWindow {
    fn default() -> Self {
        Self::new(
            String::from("Lunar_Engine_Instance"),
            1280.0,
            720.0,
        )
    }
}
