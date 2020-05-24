use winit::{
    dpi::LogicalSize, CreationError, Event, EventsLoop, Window, WindowBuilder, WindowEvent,
};

#[derive(Debug)]
pub struct LunarWindow {
    pub events_loop: EventsLoop,
    pub window: Window,
}

impl LunarWindow {
    pub fn new<T: Into<String>>(title: T, size: LogicalSize) -> Result<Self, CreationError> {
        let events_loop = EventsLoop::new();
        let output = WindowBuilder::new()
            .with_title(title)
            .with_dimensions(size)
            .build(&events_loop);
        output.map(|window| Self {
            events_loop,
            window
        })
    }
}

impl Default for LunarWindow {
    fn default() -> Self {
        Self::new(
            "Lunar_Engine_Instance",
            LogicalSize {
                width: 1280.0,
                height: 720.0,
            },
        )
        .expect("could not create a window")
    }
}
