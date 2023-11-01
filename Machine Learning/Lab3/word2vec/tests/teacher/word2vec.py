import csv
import gzip
import gensim
import pickle
import logging
import argparse
import numpy as np

# Configuring logging
logging.basicConfig(level=logging.DEBUG)

# Model Config
VectorSize = 300
WindowSize = 15
MinCount = 2

# Input Files
DataTR = "../Files/reviews_data.txt.gz"


def read_args():
	parser = argparse.ArgumentParser(description='Os parametros sao:')
	parser.add_argument('-m', '--method', type=str, required=True, help='1 - Media, 2 - Mediana')
	return parser.parse_args()


def read_input(input_file):
	"""This method reads the input file which is in gzip format"""

	logging.info("reading file {0}...this may take a while".format(input_file))

	with gzip.open(input_file, 'rb') as f:
		for i, line in enumerate(f):
			if (i % 10000) == 0:
				logging.info("read {0} reviews".format(i))

			yield gensim.utils.simple_preprocess(line)


def read_and_train():
	documents = list(read_input(DataTR))
	print("Done reading data file")

	print("Training model")
	model = gensim.models.Word2Vec(documents, vector_size=VectorSize, window=WindowSize, min_count=MinCount, workers=10)
	model.train(documents, total_examples=len(documents), epochs=10)
	print("Model trained")
	
	return model


def save_model(model):
	print ('Saving Model into modelogensin file...')

	file = open("modelogensim", 'wb')
	pickle.dump(model, file)
	file.close()


def open_model():
	file = open("modelogensim", 'rb')
	model = pickle.load(file)
	file.close()

	return model


def read_csv():
	labels = {"neg": 0, "pos": 1}
	reviews = []
	
	with open('imdb_master.csv', encoding="ISO-8859-1") as csvfile:
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
				v_mean.append(np.zeros(VectorSize))

		if metric == 1:
			result.append(np.mean(v_mean, axis=0))
		else:
			result.append(np.median(v_mean, axis=0))
		
	return result


def write_results(result, reviews):
	print('Saving train.txt file...')
	file = open("train.txt", "w")
	result_len = len(result)

	for i in range(0, int(result_len / 2)):

		line = str(reviews[i][0][1]) + " "
		for j in range(0, len(result[i])):
			line = line + str(j) + ":" + str(result[i][j]) + " "

		line = line + " "  +  "\n"
		file.write(line)

	file.close()

	print ('Saving train.txt file...')
	file = open("test.txt", "w")

	for i in range(int(result_len / 2), result_len):

		line = str(reviews[i][0][1]) + " "
		for j in range(0, len(result[i])):
			line = line + str(j) + ":" + str(result[i][j]) + " "

		line = line + " "  + "\n"
		file.write(line)

	file.close()


if __name__ == "__main__":
	# Reading the extract features method
	args = read_args()
	m = int(args.method)

	# Reading the file DataTR to train de word2Vec model
	model = read_and_train()

	# Reding the CSV file to getter the features
	reviews = read_csv()

	# Getting the features
	results = extract_features(model, reviews, m)

	# Creating the files train.txt and test.txt
	write_results(results, reviews)

	# #save_model(model)
	# #model = open_model()
	
