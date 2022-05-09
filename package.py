# -*- coding: utf-8 -*-

name = 'turret_klf'

version = '1.1.13'

authors = ['daniel.flood', 'ben.skinner', 'wen.tan', 'naomi.que', 'jonah.newton']

build_requires = [
                  'python',
                  'turret_lib-1.1.22+<2',
                  'cmake-3.2'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'katana-3.0.7', 'tbb-4'],
    ['platform-linux', 'arch-x86_64', 'katana-3.6.2', 'tbb_katana-2017'],
    ['platform-linux', 'arch-x86_64', 'katana-4.5.2', 'tbb_katana-2019.6']
]

def commands():
    env.KATANA_RESOURCES.append('{root}/Resources')
    env.TURRET_AUTOLOOKFILEASSIGN_LOG_LEVEL.set("1")

    env.TURRET_CACHE_EXTERNAL.set("1")
