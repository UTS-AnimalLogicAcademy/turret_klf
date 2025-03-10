# -*- coding: utf-8 -*-

name = 'turret_klf'

version = '1.4.0'

authors = ['daniel.flood', 'ben.skinner', 'wen.tan', 'naomi.que', 'jonah.newton']

build_requires = [
                  'python',
                  'turret_lib',
                  'cmake-3',
                  'devtoolset-7+'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'katana-7.0', 'tbb_katana-2020.3', 'boost_katana-1.80'],
    ['platform-linux', 'arch-x86_64', 'katana-8.0', 'tbb_katana-2020.3', 'boost_katana-1.82'],
]

def commands():
    env.KATANA_RESOURCES.append('{root}/Resources')
    env.TURRET_AUTOLOOKFILEASSIGN_LOG_LEVEL.set("1")

    env.TURRET_CACHE_EXTERNAL.set("1")
