# FFTPrice

You need to install pybind and eigen as submodules

```
git submodule update --init --recursive
```

Compile the bindings running the bash script `compile_bindings.sh`

Install the packages as editable in your current python env

`uv pip install -e .`

Test your code in Python