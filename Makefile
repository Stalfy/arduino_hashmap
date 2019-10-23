# Directories.
RELEASE_DIR  = HashMap

release:
	zip $(RELEASE_DIR).zip $(RELEASE_DIR)/*
