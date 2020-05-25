#![allow(warnings)]
extern crate LunarEngine;

fn main() {
    let mut LEngine = LunarEngine::LunarEngineCore::Engine::LunarEngine::init_engine();
    LEngine.render_loop();
}
