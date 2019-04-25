# Samples
[English](README.md) | [Русский](README_RU.md)

## Directory structure
		database	Databases that are required by reports
		reports		Reports files

## Reports folders' structure note
The parent folder's name of the report file means the name of the database that it needs.

## Samples description
### image
		sample.imagefromdb.qreport		demonstration of images loading from the database to the report

### main
		sample.graphics.qreport			demonstration of graphics elements
		sample.groupfooter.qreport		demonstration of using "group" and "groupfooter" tags
		sample.groupheader.qreport		demonstration of using "group" and "groupheader" tags
		sample.image.qreport			demonstration of images loading from LFS
		sample.list.qreport			simple output of data list
		sample.listleftjoin.qreport		output of datalist with query that constains left outer join
		sample.manual.qreport			output of datalist in tabular form
		sample.multigroup.qreport		demonstration of nested grouping
		sample.summary.qreport			demonstration of using "summary" tag
		sample.variable.qreport			demonstration of using "variable" tag
		sample.added_plus_row.qreport		calculations in "CDATA" tag
		sample.students_onlyPM.qreport		query with "like" operator

### test, test-images
This reports are required for coverage tests.
