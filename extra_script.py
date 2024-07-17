Import('env')

def add_aliases(*args, **kwargs):
    env.AddPostAction("checkprogsize", env.VerboseAction("pio device monitor -p /dev/ttyUSB0", "Opening Serial Monitor..."))

env.AddPreAction("upload", add_aliases)
