### Overview

This package contains my learnings on Competitive Programming field, including the the templates, learnings and exercises I have done so far.

### How To Use

I have the following command set up in `.zshrc` that I use to quickly create new files using my templates.

```
cpt() {
    TEMPLATE_DIR=~/projects/coding/templates
    FILENAME=${2:-hello}
    case "$1" in
        py)
            cp "$TEMPLATE_DIR/template.py" ./$FILENAME.py
            ;;
        cpp)
            cp "$TEMPLATE_DIR/template.cpp" ./$FILENAME.cpp
            ;;
        java)
            cp "$TEMPLATE_DIR/template.java" ./$FILENAME.java
            ;;
        *)
            echo "Usage: cpt [py|cpp|java]"
            ;;
    esac
}
```