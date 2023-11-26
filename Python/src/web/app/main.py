import asyncio
from src.web.app.controllers import control_panel
from blacksheep import Application

# Run using: uvicorn src.web.app.main:app --port 8000 --reload
app = Application()

async def configure_background_tasks(app):
    asyncio.get_event_loop().create_task(control_panel.monitor_mqtt())

app.on_start += configure_background_tasks
app.serve_files('src/web/app/static')