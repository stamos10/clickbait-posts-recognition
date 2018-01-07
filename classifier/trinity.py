import pymysql
import math
from statistics import mode



def Main():

	
	propabilities_given_c = []
	propabilities_given_not_c = []
	propabilities_given_c_review = []
	propabilities_given_not_c_review = []
	actual_classifications = []
	model_classifications = []
	counter = 0
	counterp = 0
	check = 0
	alert = 0
	sen = 0
	b = 5837;
	b_not = 14301
	c = 6914
	step = 1
	correct_answer = 0
	idf = 0
	N = 1990
	laplace = 1
	laplaceb = 3.5
	labelling = 'none'
	TP = 0
	TN = 0
	FP = 0
	FN = 0

	print("{\"results\":[")
	print("\n \n")

	try:
		connection=pymysql.connect(host='127.0.0.1', user='', password='', database='bag_of_words', charset='utf8mb4', cursorclass=pymysql.cursors.DictCursor)
		cur=connection.cursor()
		
		


		cur.execute("select * from LABELS where id<2000")
		documents=cur.fetchall()
		
		for row_doc in documents:
			print("{\"Document number\":\"", step, "\",")			
			
			cur.execute("select * from final_data where Document_id=%s and Section='postText'", (row_doc['Document_id']))
			features=cur.fetchall()
				
			for row in features:
				cur.execute("select count(distinct Document_id) from final_data where Feature=%s and Section='postText'", row['Feature'])
				docs= cur.fetchall()
				for d in docs:
					if (d['count(distinct Document_id)'] is not None):
						df = int(d['count(distinct Document_id)'])
						idf = math.log((N / (df + 0.001)), 10)
						idf = float(idf)
						tfidf = df * idf

				if idf < 2.99:

	
					cur.execute("select sum(Num), Feature from final_data where Feature=%s and Label='clickbait' and Section='postText'", row['Feature'])
					num = cur.fetchall()
					
					print("\"[Term Processed]\": \"%s\"," % row['Feature'])
					for row_b in num:
							
						if (row_b['sum(Num)'] is not None):
							a = int(row_b['sum(Num)'])
							counterp += 1
							m_nb = (a + laplace) / (b + c)
							propabilities_given_c.append(m_nb)
							
						else:
							a = 0
							m_nb = (a + laplace) / (b + c)
							propabilities_given_c.append(m_nb)		
							

					cur.execute("select sum(Num), Feature from final_data where Feature=%s and Label='no-clickbait' and Section='postText'", row['Feature'])
					num_b = cur.fetchall()
					
					for row_c in num_b:
						
						if (row_c['sum(Num)'] is not None):
							a_not = int(row_c["sum(Num)"])
							counter += 1
							if counter < 1:
								tease = row_c['Feature']
								alert = check_if_teaser(tease.strip(' \t\n\r'))
							sent = row_c['Feature']
							sen += check_sentiment(sent.strip('\t\n\r'))
							
							m_nb_not = (a_not + laplace) / (b_not + c)
							propabilities_given_not_c.append(m_nb_not)

						else:
							a_not = 0
							m_nb_not = (a_not + laplace) / (b_not + c)
							propabilities_given_not_c.append(m_nb_not)
							
							
							
			clickbait = classify_yes(propabilities_given_c)
			no_clickbait = classify_no(propabilities_given_not_c)
				
		
			r_yes = math.exp(clickbait)/ (math.exp(clickbait) + math.exp(no_clickbait))
			r_no = math.exp(no_clickbait)/ (math.exp(clickbait) + math.exp(no_clickbait))
			
			if alert == 1:
				r_yes += 0.08			

			if sen == 1:
				r_yes += 0.05
			elif sen > 1:
				r_yes += 0.10


			print("\"[Document id]\": \"%s\"," % row_doc['Document_id'])			
			print("\"[Clickbait Score]\": \"%f\"," % r_yes)
			print("\"[Class Should Be]\":\"", row_doc['Label'], "\",")
			actual_label = row_doc['Label']			
			if  actual_label.strip() == "clickbait":
				actual_classifications.append(1)
			elif actual_label.strip() == "no-clickbait":
				actual_classifications.append(0) 
			if r_yes > 0.55:
				labelling = "clickbait"
				model_classifications.append(r_yes)
				print ("\"[Trinity Class]\":\"", labelling, "\",")
				if r_yes > 0.70:
					print ("\"[Trinity Characterization]\":\"heavily click baiting\"")
				else:
					print ("\"[Trinity Characterization]\":\"considerably click baiting\"")
			elif r_yes < 0.45:
				labelling = "no-clickbait"
				model_classifications.append(r_yes)
				print("\"[Trinity Class]\":\"", labelling, "\",")
				if r_yes < 0.30:
					print ("\"[Trinity Characterization]\":\"not click baiting\"")
				else:
					print ("\"[Trinity Characterization]\":\"slightly click baiting\"")
			else: 
				cur.execute("select * from final_data where Document_id=%s and Section='postText'", (row_doc['Document_id']))
				featuresb=cur.fetchall()
				
				for rowb in featuresb:
					cur.execute("select count(distinct Document_id) from final_data where Feature=%s and Section='postText'", rowb['Feature'])
					docsb= cur.fetchall()
					for db in docsb:
						if (db['count(distinct Document_id)'] is not None):
							dfb = int(db['count(distinct Document_id)'])
							idfb = math.log((N / (dfb + 0.001)), 10)
							idfb = float(idfb)
							

					if idfb > 1.60 and idfb < 2.99:
					
						cur.execute("select sum(Num), Feature from final_data where Feature=%s and Label='clickbait' and Section='postText'", rowb['Feature'])
						numb = cur.fetchall()
					
					
						for row_b in numb:
						
							if (row_b['sum(Num)'] is not None):
								ab = int(row_b['sum(Num)'])
								m_nbb = (ab + laplaceb) / (b + c)
								propabilities_given_c_review.append(m_nbb)
							
							else:
								ab = 0
								m_nbb = (ab + laplaceb) / (b + c)
								propabilities_given_c_review.append(m_nbb)
															
																

						cur.execute("select sum(Num), Feature from final_data where Feature=%s and Label='no-clickbait' and Section='postText'", rowb['Feature'])
						num_bb = cur.fetchall()
					
						for row_c in num_bb:
						
							if (row_c['sum(Num)'] is not None):
								a_notb = int(row_c["sum(Num)"])
								m_nb_notb = (a_notb + laplaceb) / (b_not + c)
								propabilities_given_not_c_review.append(m_nb_notb)
							
							else:
								a_notb = 0
								m_nb_notb = (a_notb + laplaceb) / (b_not + c)
								propabilities_given_not_c_review.append(m_nb_notb)	
							
							
				clickbaitb = classify_yes(propabilities_given_c_review)
				no_clickbaitb = classify_no(propabilities_given_not_c_review)
				
		
				r_yesb = math.exp(clickbaitb)/ (math.exp(clickbaitb) + math.exp(no_clickbaitb))
				r_nob = math.exp(no_clickbaitb)/ (math.exp(clickbaitb) + math.exp(no_clickbaitb))
				score = 0.48
				
				if r_yesb > 0.56:
					labelling = "clickbait"
					model_classifications.append(r_yesb * 0.97)
					print("\"[Clickbait Score] [REVALUATION REQUESTED]\": \"%f\"," % r_yesb)
					print ("\"[Trinity Class]\":\"", labelling, "\",")
					print ("\"[Trinity Characterization]\":\"considerably click baiting\"")

				else:

					if counter > counterp:
						score -= 0.03
					elif counter < counterp:
						score += 0.03
					
					if r_yesb > 0.48 and r_yes > 0.48 or r_yesb > 0.53:
						score += 0.055

					if score > 0.50:
						labelling = "clickbait"
						model_classifications.append(r_yesb * 0.97)
						print("\"[Clickbait Score] [REVALUATION REQUESTED]\": \"%f\"," % r_yesb)
						print ("\"[Trinity Class]\":\"", labelling, "\",")
						print ("\"[Trinity Characterization]\":\"considerably click baiting\"")
					else:
						labelling = "no-clickbait"
						model_classifications.append(r_yes)
						print("\"[Clickbait Score] [REVALUATION REQUESTED]\": \"%f\"," % r_yesb)
						print("\"[Trinity Class]\":\"", labelling, "\",")
						print ("\"[Trinity Characterization]\":\"slightly click baiting\"")
				del propabilities_given_c_review[:]
				del propabilities_given_not_c_review[:]
				
			print("},")
			print("\n")

			correct_label = row_doc['Label'] 
			if labelling.strip() == correct_label.strip():
				correct_answer += 1

			if labelling.strip() == "clickbait" and correct_label.strip() == "clickbait":
				TP += 1
			if labelling.strip() == "clickbait" and correct_label.strip() == "no-clickbait":
				FP += 1
			if labelling.strip() == "no-clickbait" and correct_label.strip() == "no-clickbait":
				TN += 1
			if labelling.strip() == "no-clickbait" and correct_label.strip() == "clickbait":
				FN += 1
			del propabilities_given_c[:]
			del propabilities_given_not_c[:]

			counter = 0
			counterp = 0
			alert = 0
			sen = 0
			step+=1

	

	except pymysql.Error as e:
		if(connection):
			print ("MySQL Error: %s", e)
			connection.rollback()
	finally:
		if(connection):
			connection.close()
	print("{\"Total Answers\":\" %d\"," % (step - 1))
	print("\"Correct Answers\":\" %d\"}" % correct_answer)
	
	print("\"TP\": \"%f\"," % TP)
	print("\"TN\": \"%f\"," % TN)
	print("\"FN\": \"%f\"," % FN)
	print("\"FP\": \"%f\"," % FP)
	F_score = (2 * TP) / ((2 * TP) + FP + FN)
	F_score = float(F_score)
	precision = TP / (TP + FP)
	recall = TP / (TP + FN)
	mse = calculate_mse(actual_classifications, model_classifications)
	print("\"Fscore\": \"%f\"" %F_score)
	print("\"Precision\": \"%f\"" %precision)
	print("\"Recall\": \"%f\"" %recall)
	print("\"MSE\": \"%f\"" %mse)
	print("]}")


def classify_yes(propab = []):

	total_prop = 0;
	prior_yes = math.exp(math.log(0.3))
	
	for x in propab:
		total_prop += math.exp(math.log(x))
		
	if total_prop == 0:
		total_prop = 0.000000000000000001	
	result_yes = math.log(total_prop)
	
	return  float(result_yes) 



def classify_no(propab = []):

	total_prop = 0;
	prior_no = math.exp(math.log(0.7))
		
	for x in propab:
		total_prop += math.exp(math.log(x))

	if total_prop == 0:
		total_prop = 0.000000000000000001
	result_no = math.log(total_prop)
	
	return  float(result_no)




def check_if_teaser(feature):

	num = 0
	teasers = ['incredible', 'amazing', 'unbelievable', 'why', 'that', 'those', 'these', 'could', 'should', 'may', 'new', 'she', 'him', 'you', 'will', 'not', 'top', 'hot', 'how', 'best', 'why', 'who', 'was', 'most', 'just', 'then', 'school' 'favourite', 'favorite', 'sex', 'sexist', 'sexy', 'some', 'where', 'way', 'ways', 'this', 'perfect', 'things', 'which', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten', 'eleven', 'twelve', 'thirteen', 'fifteen', 'twenty', 'thirty']

	if feature in teasers:
		num = 1

	for x in teasers:
		if len(feature) > 3:
			if feature[1:-1] == x[1:-1]:
				num = 1

	return num



def check_sentiment(feature):

	num = 0
	sentiments = ['adorable', 'amazing', 'breathtaking', 'delightful', 'desirable',  'easiest', 'ecstatic', 'excited', 'excitement',   'extraordinary', 'fabulus', 'fabulously', 'fantastic', 'fascinate', 'fascinating', 'fashionable', 'favorite', 'gloriously', 'gorgeous', 'gorgeously', 'grateful', 'humorous', 'idyllic', 'incredible', 'incredibly', 'irresistible', 'magnificent', 'marvelous', 'marvellous', 'miraculous', 'miraculously', 'outstanding', 'passionate', 'phenomal', 'promising', 'refreshing', 'romantic', 'romantically', 'sensation', 'sensational', 'sweet', 'sweethart', 'unforgettable', 'wonderful', 'wonderfully', 'top', 'hot', 'best']

	if feature in sentiments:
		num = 1

	for x in sentiments:
		
		if feature[0:-1] == x[0:-1]:
			num = 1

	return num



def calculate_mse(actual = [], model = []):

	store = []
	total = 0.0
	for x, y in zip(actual, model):
				
		store.append( x - y)	
	

	for a in store:
		total += math.pow(a, 2)

	result = total / (430 - 2)

	result = float(result)
	return result




	

if __name__ == '__main__':
	Main()
