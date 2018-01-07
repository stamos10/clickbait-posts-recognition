# clickbait-posts-recognition

--------------------------------------------------------------------
Text Classification Project - README.txt


Date: 7/1/2018
Version: 1.0
Author: Stamatis Strongylis
Approach: Multinomial Naive Bayes - Custom Approach with custom C and Python3 
--------------------------------------------------------------------







--------------------------------------------------------------------
1.GENERAL
--------------------------------------------------------------------


	1.1 Files and Database
	----------------------
  **********************************************************************
  Old - unused folders
	
  folder: clickbait/src

	a. reader.c
	b. tokenizer_truth.c
	c. configure_database.c
	d. tokenizer.c

	folder: diplwmatiki/clickbait/

	a. sweep.py
	b. tidiness.py
	c. classifier.py
  
  
  *************************************************************************
Version 1.0 folders

folder validation_data/src

  a. reader.c
	b. tokenizer_truth.c
	c. configure_database.c
	d. tokenizer.c


folder test_data/src

  a. reader_test.c
	b. tokenizer_truth_test.c
	c. configure_database_test.c
	d. tokenizer_test.c


folder classifier

  a. trinity.py



NOTE 1: Files are to be executed in above order of appearance
 



1.2 Database
----------------------

Name: bag_of_words
Tables: LABELS, final_data, val_data, TEST_LABELS, test_data





--------------------------------------------------------------------
2.DATASETS
--------------------------------------------------------------------

Dataset: http://www.uni-weimar.de/medien/webis/corpora/corpus-webis-clickbait-17/clickbait17-train-170331.zip

Dataset document collection: the whole collection consists of 2495 documents



	2.1 Usage
	----------------------

	Training Data: 1993 documents

	Validation Data: 430 documents

  Test data: 430 documents


	2.2 Labels
	----------------------

	In this collection 1697 docs are labelled as no-clickbait and 762 as clickbait






--------------------------------------------------------------------
3.DATA PREPARATION - Stage 1
--------------------------------------------------------------------


NOTE: This project is configured to work with the above Dataset


	3.1 reader.c
	---------------------

	This file is optional. It converts the instances.jsonl file to a pretty formatted JSON File.



	3.2 tokenizer_truth.c
	---------------------

	This file reads the truth.jsonl file and inserts into LABELS table Documents ids and Labels, as these will be needed later



	3.3 configure_database.c
	------------------------

	This file must be run before tokenizer.c as it perfoms all the database preparation and table creation



	3.4 tokenizer.c
	---------------------

	This file reads the (a)instances.json (created from instances.jsonl in step 3.1) file , (b) LABELS table and populates data table with relevant data for each Feature


		3.4.1 tokenizer.c - Operation Details
        	-------------------------------------

		1. Stop Words: a very small stop words List is used consisting of 10 words
		2. Tokenization is perfomed 
		3. Words with length less than 2 characters are ignored as well as words with length grater than 21 characters (to avoid links entering the database)
		4. All special characters and punctuation characters are ignored
		5. Section of appearance of each word is saved (in case weighted zone scoring is to be used)
		6. Number of occurence of each term given class for each dodument is saved (bag of words model)







--------------------------------------------------------------------
4.CLASSIFICATION
--------------------------------------------------------------------


	5.1 trinity.py
	-----------------

	The classifier will use as vocabulary the Features contained in the final_data table

	The classifier follows the Multinomial Naive Bayes Model and produces log values as 'clickbait score', 'no clickbait score', as well as Labelling and confidence values



--------------------------------------------------------------------
5.CHARACTERISTICS
--------------------------------------------------------------------


 
1. Laplace Smoothing: to eliminate 0s and handle unseen words











