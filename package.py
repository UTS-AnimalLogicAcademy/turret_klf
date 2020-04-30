# -*- coding: utf-8 -*-

name = 'turret_klf'

version = '1.1.10'

authors = ['daniel.flood', 'ben.skinner', 'wen.tan']

requires = ['tbb']

build_requires = [
                  'python',
                  'turret_lib-1.1.18+<2',
                  'cmake-3.2'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'katana-3.0.7']
   ['platform-linux', 'arch-x86_64', 'katana-3.5.1'],
   ['platform-linux', 'arch-x86_64', 'katana-3.5.2']
]

def commands():
    env.KATANA_RESOURCES.append('{root}/Resources')
    env.TURRET_AUTOLOOKFILEASSIGN_LOG_LEVEL.set("1")

    env.TURRET_CACHE_EXTERNAL.set("1")
