#!/usr/bin/env python3

# Hacky script to download linux and windows typed_ast wheels from appveyor and gcloud

import os
import os.path
import json
import sys
from urllib.request import urlopen

# Appveyor download for windows wheels
api_url = 'https://ci.appveyor.com/api/'
def get_json(path):
    url = api_url + path
    f = urlopen(url)
    data = f.read()
    return json.loads(data)

def download(url):
    print('Downloading', url)
    name = os.path.join('dist', os.path.split(url)[1])
    with urlopen(url) as f:
        data = f.read()
    with open(name, 'wb') as f:
        f.write(data)


def download_appveyor(version):
    project_base = 'projects/ddfisher/typed-ast-a4xqu'
    history = get_json(project_base + '/history?recordsNumber=20')
    for build in history['builds']:
        if build.get('tag') == version:
            build_version = build['version']
            build_version = str(build['buildId'])
            break
    else:
        sys.exit("Couldn't find tag")
    print(build_version)

    build = get_json(project_base + '/builds/' + build_version)
    for job in build['build']['jobs']:
        artifact_url = 'buildjobs/{}/artifacts'.format(job['jobId'])
        artifacts = get_json(artifact_url)
        for artifact in artifacts:
            download(api_url + artifact_url + '/' + artifact['fileName'])

# gcloud downloads for linux wehels
MIN_VER = 5
MAX_VER = 8

GCLOUD_URL = "https://storage.googleapis.com/typed-ast/typed_ast-{version}-cp3{pyver}-cp3{pyver}m-{platform}.whl"

def download_entries(base_url, version, platform):
    entries = ""
    for pyver in range(MIN_VER, MAX_VER + 1):
        url = base_url.format(
            version=version,
            pyver=pyver,
            platform=platform)
        download(url)

def main(argv):
    if len(argv) != 2:
        sys.exit("Usage: download_typed_ast.py version")

    version = argv[1]
    os.makedirs('dist', exist_ok=True)

    download_entries(GCLOUD_URL, version, 'manylinux1_x86_64')
    download_entries(GCLOUD_URL, version, 'manylinux1_i686')

    download_appveyor(version)

if __name__ == '__main__':
    main(sys.argv)
