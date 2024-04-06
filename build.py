import vitis

workspace = "."
camera_program_name = "camera_program"

client = vitis.create_client()
client.set_workspace(workspace)
camera_program = client.get_component(camera_program_name)
camera_program.build()
vitis.dispose()
