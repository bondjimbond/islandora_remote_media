# Islandora Remote Media Solution Pack

An Islandora Solution Pack that allows for ingesting and playing media hosted elsewhere on the web, using media embed code provided by the remote host.

## Introduction

This solution pack manages metadata-only records for media objects (video, audio, possibly others) that are hosted elsewhere on the Web.
The media's embed code is stored in the object's OBJ datastream, which is editable if changes need to be made after ingesting. The object's View page is
similar to any other Islandora object, except instead of using Islandora's viewer to display a local object, the page shows an embedded viewer from
the remote resource.

The use case for this solution pack is to make externally-hosted media discoverable in the repository and to expose it to harvesters.

This is particularly useful if storage is expensive, as Islandora media objects and their derivatives have high storage demands.

![Screenshot](https://i.imgur.com/F3nzfbT.png)

## Usage and Details

Remote Media objects use the Content Model `islandora:sp_remoteMediaCModel`. An ingest form is included.

Ingest a Remote Media object in the normal way. In the first step, enter the embed code provided by the remote resource. Then fill out the metadata as usual.

Embed code can be modified by editing the OBJ datastream (Manage -> Datastreams, click "edit" in the OBJ row). The OBJ datastream may also be replaced with a plaintext file (.asc or .txt).

Permissions are required to edit and replace Remote Media OBJ datastreams.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)

## Maintainer

* [Brandon Weigel](https://github.com/bondjimbond)

## Development and feedback

Bug reports, use cases and suggestions are welcome, as are pull requests. Open an issue in the repository to give feedback.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
