from invoke import task
import serial
import time


@task
def build(ctx, prog=False, run=False, exit=False, mon=False):
    ctx.run("make -j16")
    if prog:
        program(ctx, run, exit)
    if mon:
        monitor(ctx)


@task
def clean(ctx):
    ctx.run("make clean")
    ctx.run("rm -rf platform")


@task
def program(ctx, run=False, exit=False):
    ctx.run(
        f"$XILINX_VITIS_HOME/xsdb scripts/load.tcl run={str(run).lower()} exit={str(exit).lower()}"
    )


@task
def monitor(ctx, port="", baud=115200):
    if not port:
        with open(".monitor_port", "r") as f:
            port = f.readlines()[0]
    else:
        with open(".monitor_port", "w") as f:
            f.write(port)
    ser = serial.Serial(port=port, baudrate=baud, timeout=0.01)
    while True:
        data = ser.readline()
        if data:
            print(data.decode(errors="ignore"), end="", flush=True)
        time.sleep(0.01)


@task
def create_platform(ctx):
    ctx.run("rm -rf platform")
    ctx.run(f"$XILINX_VITIS_HOME/xsct scripts/create_platform.tcl")


@task
def build_platform(ctx):
    ctx.run(f"$XILINX_VITIS_HOME/xsct scripts/build_platform.tcl")
    ctx.run(
        "mv ./platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/lib/outbyte.o ./platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/lib/outbyte.obckp"
    )
    ctx.run(
        "mv ./platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/lib/inbyte.o ./platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/lib/inbyte.obckp"
    )


@task
def update_platform_xsa(ctx, xsa_file):
    ctx.run(f"$XILINX_VITIS_HOME/xsct scripts/update_platform_xsa.tcl {xsa_file}")
    print("Building platform")
    build_platform(ctx)


@task
def create_flash_image(ctx):
    return


@task
def load_flash_image(ctx):
    return
