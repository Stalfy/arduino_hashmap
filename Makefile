# Directories.
RELEASE_DIR  = HashMap

release:
	zip -r $(RELEASE_DIR).zip $(RELEASE_DIR)/*
