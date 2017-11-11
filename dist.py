import glob
import os


EXTS = ['*.cpp', '*.hpp', '*.h']
RABISH = ['RemoteProcessClient.cpp', 'RemoteProcessClient.h',
          'Runner.cpp', 'Runner.h', 
          'Strategy.h', 'Strategy.cpp']



def get_files():
    files = []
    for ext in EXTS:
        files += glob.glob(ext)
    for rab in RABISH:
        try:
            files.remove(rab)
        except:
            pass
    return files


def make_dist():
    files = get_files()
    os.system('rm dist/dist.zip ')
    os.system('zip dist/dist.zip ' + ' '.join(files))


if __name__ == '__main__':
    make_dist()
