# -*- coding: utf-8 -*-

name = 'turret_klf'

version = '1.2.7'

authors = ['daniel.flood', 'ben.skinner', 'wen.tan', 'naomi.que', 'jonah.newton']

build_requires = [
                  'python',
                  'turret_lib',
                  'cmake-3',
                  'devtoolset-7+'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'katana-6.5', 'tbb_katana-2020.3', 'boost_katana-1.76']
]

def commands():
    env.KATANA_RESOURCES.append('{root}/Resources')
    env.TURRET_AUTOLOOKFILEASSIGN_LOG_LEVEL.set("1")

    env.TURRET_CACHE_EXTERNAL.set("1")
