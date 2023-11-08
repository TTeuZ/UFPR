import csv
import gensim
import pickle
import logging

# Params Values
vector_sizes = [250, 300, 350, 400, 500]
windows = [5, 10, 15]
counts = [2, 5, 10]

# Input Files
DataTR = "../../Files/imdb_master.csv"

# Configuring logging
logging.basicConfig(level=logging.DEBUG)


def read_input(input_file):
    """This method reads the input file which is in gzip format"""

    logging.info("reading file {0}...this may take a while".format(input_file))

    with open(input_file, encoding="ISO-8859-1") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if (row["label"] == "unsup"):
                yield gensim.utils.simple_preprocess(str(row))


def train(documents, size, window, count):
    print("Training model")
    model = gensim.models.Word2Vec(
        documents, vector_size=size, window=window, min_count=count, workers=10)
    model.train(documents, total_examples=len(documents), epochs=10)
    print("Model trained")

    return model


def save_model(model, path):
    print('Saving Model into modelogensin file...')

    file = open(path, 'wb')
    pickle.dump(model, file)
    file.close()


if __name__ == "__main__":
    documents = list(read_input(DataTR))
    print("Done reading data file")

    for size in vector_sizes:
        for window in windows:
            for count in counts:
                path = f"../imdb_master/models/word2vec_{size}_{window}_{count}"

                # training the model
                model = train(documents, size, window, count)

                # Save the model for reuse
                save_model(model, path)
