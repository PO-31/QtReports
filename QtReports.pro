TEMPLATE = subdirs

SUBDIRS += qtreports qtreports-tests qtreports-viewer
#SUBDIRS += qtreports qtreports-viewer
qtreports-tests.depends = qtreports
qtreports-viewer.depends = qtreports
