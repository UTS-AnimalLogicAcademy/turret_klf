# -*- coding: utf-8 -*-

name = 'turret_klf'

version = '0.1.0'

authors = ['daniel.flood']

build_requires = [
                  'python',
                  'turret_lib'
           ]

variants = [
    ['platform-linux', 'arch-x86_64', 'katana-3.0.1'],
    ['platform-linux', 'arch-x86_64', 'katana-3.1.1']
]

def commands():
    env.KATANA_RESOURCES.append('{root}/Resources')
    env.ALA_AUTOLOOKFILEASSIGN_LOG_LEVEL.set("1")
    env.ZMQ_CACHE_QUERIES.set("1")
    env.ZMQ_CACHE_EXTERNAL.set("1")
