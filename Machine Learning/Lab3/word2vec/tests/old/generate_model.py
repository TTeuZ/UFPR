import gzip
import gensim
import pickle
import logging

import config

# Configuring logging
logging.basicConfig(level=logging.DEBUG)


def read_input(input_file):
	"""This method reads the input file which is in gzip format"""

	logging.info("reading file {0}...this may take a while".format(input_file))

	with gzip.open(input_file, 'rb') as f:
		for i, line in enumerate(f):
			if (i % 10000) == 0:
				logging.info("read {0} reviews".format(i))

			yield gensim.utils.simple_preprocess(line)


def read_and_train():
	documents = list(read_input(config.DataTR))
	print("Done reading data file")

	print("Training model")
	model = gensim.models.Word2Vec(documents, vector_size=config.VectorSize, window=config.WindowSize, min_count=config.MinCount, workers=10)
	model.train(documents, total_examples=len(documents), epochs=10)
	print("Model trained")
	
	return model


def save_model(model, path):
	print ('Saving Model into modelogensin file...')

	file = open(path, 'wb')
	pickle.dump(model, file)
	file.close()


if __name__ == "__main__":
    path = f"../models/word2vec_{config.VectorSize}_{config.WindowSize}_{config.MinCount}_{config.method}"

	# training the model
    model = read_and_train()

	# Save the model for reuse
    save_model(model, path)