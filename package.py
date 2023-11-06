# -*- coding: utf-8 -*-

name = 'turret_klf'

version = '1.1.17'

authors = ['daniel.flood', 'ben.skinner', 'wen.tan', 'naomi.que', 'jonah.newton']

build_requires = [
                  'python',
                  'turret_lib',
                  'cmake-3'
		  #'devtoolset-9'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'katana-3.0.7', 'tbb-4'],
    ['platform-linux', 'arch-x86_64', 'katana-3.6.2', 'tbb_katana-2017'],
    ['platform-linux', 'arch-x86_64', 'katana-4.5.2', 'tbb_katana-2019.6', 'boost_katana-1.70', 'devtoolset-6'],
    ['platform-linux', 'arch-x86_64', 'katana-5', 'tbb_katana-2019.6', 'boost_katana-1.70', 'devtoolset-6'],
    ['platform-linux', 'arch-x86_64', 'katana-6.0.1', 'tbb_katana-2020.3', 'boost_katana-1.76', 'devtoolset-9']
]

def commands():
    env.KATANA_RESOURCES.append('{root}/Resources')
    env.TURRET_AUTOLOOKFILEASSIGN_LOG_LEVEL.set("1")

    env.TURRET_CACHE_EXTERNAL.set("1")
