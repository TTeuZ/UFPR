import csv
import gensim
import pickle
import logging
import numpy as np

import config

# Configuring logging
logging.basicConfig(level=logging.DEBUG)


def open_model(path):
	file = open(path, 'rb')
	model = pickle.load(file)
	file.close()

	return model


def read_csv(path):
	labels = {"neg": 0, "pos": 1}
	reviews = []
	
	with open(path, encoding="ISO-8859-1") as csvfile:
		reader = csv.DictReader(csvfile)
		for row in reader:
			if not(row['label'] == "unsup"):
				reviews.append([(row['review'], labels[row['label']])])

	for j in range(0, len(reviews)):
		w = (gensim.utils.simple_preprocess(reviews[j][0][0]))
		w1 = [w, reviews[j][0][1]]
		reviews[j][0] = w1
	
	return reviews


def extract_features(model, reviews, metric):
	result = []

	print('Building Representation...')
	for j in range(0, len(reviews)):
		w = reviews[j][0][0]
		v_mean = []
		
		for k in range(0, len(w)):
			try:
				v_mean.append(model.wv[w[k]])
			except KeyError:
				v_mean.append(np.zeros(config.VectorSize))

		if metric == 1:
			result.append(np.mean(v_mean, axis=0))
		else:
			result.append(np.median(v_mean, axis=0))
		
	return result


def write_results(result, reviews):
	print('Saving train.txt file...')
	file = open(f"../features/train_{config.VectorSize}_{config.WindowSize}_{config.MinCount}_{config.method}.txt", "w")
	result_len = len(result)

	for i in range(0, int(result_len / 2)):

		line = str(reviews[i][0][1]) + " "
		for j in range(0, len(result[i])):
			line = line + str(j) + ":" + str(result[i][j]) + " "

		line = line + " "  +  "\n"
		file.write(line)

	file.close()
	
	print ('Saving test.txt file...')
	file = open(f"../features/test_{config.VectorSize}_{config.WindowSize}_{config.MinCount}_{config.method}.txt", "w")

	for i in range(int(result_len / 2), result_len):

		line = str(reviews[i][0][1]) + " "
		for j in range(0, len(result[i])):
			line = line + str(j) + ":" + str(result[i][j]) + " "

		line = line + " "  + "\n"
		file.write(line)

	file.close()


if __name__ == "__main__":
    path = f"../models/word2vec_{config.VectorSize}_{config.WindowSize}_{config.MinCount}_{config.method}"

    # Getting one of the trained models
    model = open_model(path)

    # Reding the CSV file to getter the features
    reviews = read_csv("../../files/imdb_master.csv")
	
	# Extracting the features
    results = extract_features(model, reviews, config.method)
	
    # Creating the files train.txt and test.txt
    write_results(results, reviews)