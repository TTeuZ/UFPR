import gzip
import gensim
import pickle
import logging

# Params Values
vector_sizes = [50, 100, 150, 200, 250, 300, 400, 500]
windows = [5, 10, 15, 20]
counts = [2, 5, 10]

# Input Files
DataTR = "../../files/reviews_data.txt.gz"

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


def train(documents, size, window, count):
	print("Training model")
	model = gensim.models.Word2Vec(documents, vector_size=size, window=window, min_count=count, workers=10)
	model.train(documents, total_examples=len(documents), epochs=10)
	print("Model trained")
	
	return model


def save_model(model, path):
	print ('Saving Model into modelogensin file...')

	file = open(path, 'wb')
	pickle.dump(model, file)
	file.close()


if __name__ == "__main__":
    documents = list(read_input(DataTR))
    print("Done reading data file")

    for size in vector_sizes:
        for window in windows:
            for count in counts:
                path = f"../reviews_data/models/word2vec_{size}_{window}_{count}"

                # training the model
                model = train(documents, size, window, count)

                # Save the model for reuse
                save_model(model, path)