import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        self.positives = positives
        self.negatives = negatives
        self.positiveWords = set()
        self.negativeWords = set()

        # load positive files
        file = open(positives, "r")
        # read the file line-by-line
        for line in file:
            # only append lines that does not start with ";" or "\n"
            if not line.startswith((";", "\n")):
                self.positiveWords.add(line.strip("\n"))
        file.close()

        # load negative words
        file = open(negatives, "r")
        # read the file line-by-line
        for line in file:
            # only append lines that does not start with ";" or "\n"
            if not line.startswith((";", "\n")):
                self.negativeWords.add(line.strip("\n"))
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # split string in separated words
        self.tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = self.tokenizer.tokenize(text)

        # number of words
        tokenLen = len(tokens)

        # assign scores to individual words
        score = 0
        for i in range(tokenLen):
            if tokens[i].lower() in self.positiveWords:
                score += 1
            elif tokens[i].lower() in self.negativeWords:
                score -= 1

        # total score for text
        return score
