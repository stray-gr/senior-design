import asyncio
from blacksheep import Application
from blacksheep.server.rendering.jinja2 import JinjaRenderer
from blacksheep.settings.html import html_settings
from app.controllers import control_panel

# Run using: python dev.py

app = Application()
html_settings.use(JinjaRenderer())

async def configure_background_tasks(app):
    asyncio.get_event_loop().create_task(control_panel.monitor_mqtt())

app.on_start += configure_background_tasks
app.serve_files('app/static')