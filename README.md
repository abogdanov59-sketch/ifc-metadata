# ifc-metadata
A command line tool used for transforming IFC into JSON format. The result is a flat array with objects, that looks like so:

```json
{
  "id": "301-16-17-37",
  "projectId": "3ir4vYruPFgwIKoil6nQwl",
  "author": "",
  "createdAt": "2022-09-07T11:00:15+03:00",
  "schema": "IFC2X3",
  "creatingApplication": "23.0.20.21 - Exporter 23.1.0.0 - Alternate UI 23.1.0.0",
  "metaObjects": [
    {
      "id": "3ir4vYruPFgwIKoil6nQwl",
      "name": "301-16-17-37",
      "type": "IfcProject",
      "parent": null,
      "properties": null,
      "material_id": null,
      "type_id": null
    },
    {
      "id": "3ir4vYruPFgwIKoiivFWhQ",
      "name": "отм.-2.200",
      "type": "IfcBuildingStorey",
      "parent": "3ir4vYruPFgwIKoil6nQwk",
      "properties": [
        "2WQTeXfdiDDhovj75kv9wo",
        "1YsnWV5c54bB1rZvrNL1Jv",
        "1YsnWV5c54bB1rZuXNL1Jv",
        "292aB3oLfoC$GhSDfe0TtF",
        "1YsnWV5c54bB1rZujNL1Jv",
        "3_AGd$Xpr04hLlNrx3_Z1p",
        "3_AGd$Xpr04hLlNq$3_Z1p",
        "3_AGd$Xpr04hLlNrh3_Z1p",
        "0ElD7aiHwyAg3nGYY93Ltc"
      ],
      "material_id": null,
      "type_id": null
    }
  ]
}
```

# Installation

```shell
$ git clone https://github.com/bingo-soft/ifc-metadata && cd ifc-metadata/src \
    && dotnet publish ./ifc-metadata.csproj -c Release -r linux-x64 --self-contained false --output ifc-metadata-linux-x64 \
    && chmod -R 755 ./bin/Release/net7.0/linux-x64 && chown -R www-data:www-data ./bin/Release/net7.0/linux-x64 \
    && ln -s /ifc-tools/ifc-metadata/src/bin/Release/net7.0/linux-x64/ifc-metadata /usr/local/bin/ifc-metadata
```

# Usage

```shell
$ ifc-metadata source.ifc target.json
```


