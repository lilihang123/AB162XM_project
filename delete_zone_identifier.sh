#!/bin/bash
# Delete all Zone.Identifier files (Windows NTFS alternate data streams)
# Usage: ./delete_zone_identifier.sh [target_dir]

TARGET_DIR="${1:-.}"

echo "Searching for Zone.Identifier files in: $TARGET_DIR"
echo "----------------------------------------------"

# Find and delete files ending with :Zone.Identifier
COUNT=0
while IFS= read -r -d '' file; do
    echo "Deleting: $file"
    rm -f "$file"
    ((COUNT++))
done < <(find "$TARGET_DIR" -name '*:Zone.Identifier' -print0 2>/dev/null)

# Also find files that literally have Zone.Identifier in the filename (Linux mount)
while IFS= read -r -d '' file; do
    echo "Deleting: $file"
    rm -f "$file"
    ((COUNT++))
done < <(find "$TARGET_DIR" -name '*Zone.Identifier*' -not -name '*:Zone.Identifier' -print0 2>/dev/null)

echo "----------------------------------------------"
echo "Done. Deleted $COUNT file(s)."
