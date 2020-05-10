PROJ_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."

for FILE in $(find "$PROJ_DIR/ast${1}" -type f -name "*.h" -or -name "*.c"); do
    sed -i "s/PyCompilerFlags/PegenCompilerFlags/" $FILE
done