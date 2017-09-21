# material-parser
This package parses OGRE .material files into json.


# installation
  ` npm install material-parser --save `
 
# usage
  ` node index.js [path of the .material file/s] `

the `json` file will appear in the current directory as ` material.json `

# example 

this material file:

```
material ArmPart/Diffuse
{
  receive_shadows off
  technique
  {
    pass
    {
      texture_unit
      {
        texture parts.png
      }
    }
  }
}
```
would be parsed to:

`
{"ArmPart/Diffuse":{"texture":"parts.png"}}
`
