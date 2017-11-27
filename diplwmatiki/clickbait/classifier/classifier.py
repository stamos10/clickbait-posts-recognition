import pymysql
import math




def Main():

	
	propabilities_given_c = []
	propabilities_given_not_c = []
	a = 0
	b = 1062;
	b_not = 2016;
	c = 2196;
	step = 1;
	print("NB --> Multinomial Naive Bayes Classifier")
	print("NB --> Gathering Data... Please wait...")
	print("\n")

	try:
		connection=pymysql.connect(host='127.0.0.1', user='root', password='cessna172stam', database='bag_of_words', charset='utf8mb4', cursorclass=pymysql.cursors.DictCursor)
		cur=connection.cursor()
		cur.execute("select * from LABELS")
		documents=cur.fetchall()
		for row_doc in documents:
			cur.execute("select * from final_data where Document_id=%s", row_doc['Document_id'])
			features=cur.fetchall()
			for row in features:
				cur.execute("select sum(Num) from final_data where Feature=%s and Label='clickbait'", row['Feature'])
				num = cur.fetchall()
			
				for row_b in num:
					if (row_b['sum(Num)'] is not None):
						a = int(row_b['sum(Num)'])
						m_nb = (a + 1) / (b + c)
						propabilities_given_c.append(m_nb)
					
					
					else:
						a = 0
						m_nb = (a + 1) / (b + c)
						propabilities_given_c.append(m_nb)	
	

				cur.execute("select sum(Num) from final_data where Feature=%s and Label='no-clickbait'", row['Feature'])
				num_b = cur.fetchall()
				for row_c in num_b:
					if (row_c['sum(Num)'] is not None):
						a_not = int(row_c["sum(Num)"])
						m_nb_not = (a_not + 1) / (b_not + c)
						propabilities_given_not_c.append(m_nb_not)

					else:
						a_not = 0
						m_nb_not = (a_not + 1) / (b_not + c)
						propabilities_given_not_c.append(m_nb_not)
			
			clickbait = classify_yes(propabilities_given_c)
			no_clickbait = classify_no(propabilities_given_not_c)
			print("-----------------Document Report START---------------------")
			print("Clickbait Score:", clickbait)
			print("No Clickbait Score:", no_clickbait)
			print("Clickbait Confidence:", clickbait/(clickbait + no_clickbait))
			print("No Clickbait Confidence:", no_clickbait/(clickbait + no_clickbait))
			print("************************ Result ***************************")
			if(clickbait > no_clickbait):			
				print(step,". Document ID:", row_doc['Document_id'], "CLASS => Clickbait")
			else:
				print(step,". Document ID:", row_doc['Document_id'], "CLASS => No-Clickbait")
			print("***********************************************************")			
			print("-----------------Document Report END------------------------")
			print("\n \n")
			
			del propabilities_given_c[:]
			del propabilities_given_not_c[:]
			step+=1

	

	except pymysql.Error as e:
		if(connection):
			print ("MySQL Error: %s", e)
			connection.rollback()
	finally:
		if(connection):
			connection.close()
	print("NB --> Done!")

	
	

def classify_yes(propab = []):

	total_prop = 0;
	prior_yes = math.log(0.3, 10)
	
	for x in propab:
		total_prop += math.log(x, 10)
		
	result_yes  = prior_yes + total_prop
	
	return result_yes

def classify_no(propab = []):

	total_prop = 0;
	prior_no = math.log(0.7, 10);	
	for x in propab:
		total_prop += math.log(x,10)

	result_no = prior_no + total_prop

	return result_no



	

if __name__ == '__main__':
	Main()
