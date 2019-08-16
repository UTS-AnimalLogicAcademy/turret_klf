# -*- coding: utf-8 -*-

name = 'turret_klf'

version = '1.1.2'

authors = ['daniel.flood', 'ben.skinner', 'wen.tan']

build_requires = [
                  'python',
                  'turret_lib-1+<2',
                  'cmake-3.2'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'katana-3.0.1'],
    ['platform-linux', 'arch-x86_64', 'katana-3.0.7'],
    ['platform-linux', 'arch-x86_64', 'katana-3.1.1']
]

def commands():
    env.KATANA_RESOURCES.append('{root}/Resources')


