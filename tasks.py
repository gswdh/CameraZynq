from invoke import task
import subprocess

@task
def build(ctx, prog=False):
    try:
        # Execute the command, capture stdout and stderr, and check for errors.
        result = subprocess.run(["/home/test/Xilinx/Vitis/2023.2/bin/vitis", "-source", "/home/test/Projects/CameraZynq/build.py"], check=True, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        # Print the standard output of the command.
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        # Print the standard error output of the command if it fails.
        print(f"Error: {e.stderr}")
        # Optionally, you can stop the program or handle the error differently here.
        quit()
    else:
        if prog:
            program(ctx)

@task
def program(ctx):
    try:
        # Execute the command, capture stdout and stderr, and check for errors.
        result = subprocess.run(["/home/test/Xilinx/Vitis/2023.2/bin/vitis", "-source", "/home/test/Projects/CameraZynq/program.py"], check=True, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        # Print the standard output of the command.
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        # Print the standard error output of the command if it fails.
        print(f"Error: {e.stderr}")
        # Optionally, you can stop the program or handle the error differently here.
        quit()
