# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).
import math

from util import manhattanDistance
from game import Directions
import random, util

from game import Agent
from pacman import GameState


class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """

    def getAction(self, gameState: GameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]

        if len(bestIndices) > 1:
            bestIndices = [index for index in bestIndices if legalMoves[index] != "Stop"]

        chosenIndex = random.choice(bestIndices)  # Pick randomly among the best
        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState: GameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)

        "*** YOUR CODE HERE ***"
        evaluation = 0

        # Helpers
        successorGameState = currentGameState.generatePacmanSuccessor(action)

        newPos = successorGameState.getPacmanPosition()

        oldFoodCount = currentGameState.getNumFood()
        newFoodCount = successorGameState.getNumFood()
        newFood = successorGameState.getFood().asList()

        oldCapsules = currentGameState.getCapsules()
        newCapsules = successorGameState.getCapsules()

        newGhostStates = successorGameState.getGhostStates()

        # Calc evaluation
        hasAte = abs(oldFoodCount - newFoodCount) or (abs(len(oldCapsules) - len(newCapsules)))
        foodDistances = [manhattanDistance(newPos, food) for food in newFood]
        foodDistance = min(foodDistances) if not hasAte else 0

        ghostDistances = [manhattanDistance(newPos, ghost.getPosition()) for ghost in newGhostStates if ghost.scaredTimer == 0]
        ghostDistance = min(ghostDistances) if len(ghostDistances) != 0 else 0

        evaluation = (100 / (foodDistance + 0.1)) - (100 / (ghostDistance + 0.5))

        return evaluation


def scoreEvaluationFunction(currentGameState: GameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()


class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn="scoreEvaluationFunction", depth="2"):
        self.index = 0  # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)


class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        actions = gameState.getLegalActions(0)
        scores = [self.minimaxRecursive(1, 0, gameState.generateSuccessor(0, action)) for action in actions]

        return actions[scores.index(max(scores))]

    def minimaxRecursive(self, agent, depth, gameState: GameState):
        if depth == self.depth or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)

        nextAgent = (agent + 1) % gameState.getNumAgents()
        if nextAgent == 0: depth += 1

        actions = gameState.getLegalActions(agent)
        successors = [gameState.generateSuccessor(agent, action) for action in actions]
        scores = [self.minimaxRecursive(nextAgent, depth, state) for state in successors]

        return max(scores) if agent == 0 else min(scores)


class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        alpha = -math.inf
        beta = math.inf
        scores = []

        actions = gameState.getLegalActions(0)
        for action in actions:
            score = self.betaMinimaxRecursive(1, 0, alpha, beta, gameState.generateSuccessor(0, action))
            alpha = max(alpha, score)
            scores.append(score)

        return actions[scores.index(max(scores))]
    

    def betaMinimaxRecursive(self, agent, depth, alpha, beta, gameState: GameState):
        if depth == self.depth or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)
        
        pruningValue = math.inf

        nextAgent = (agent + 1) % gameState.getNumAgents()
        if nextAgent == 0: depth += 1
        recursive = self.alphaMinimaxRecursive if nextAgent == 0 else self.betaMinimaxRecursive

        actions = gameState.getLegalActions(agent)
        for action in actions:
            state = gameState.generateSuccessor(agent, action)
            pruningValue = min(pruningValue, recursive(nextAgent, depth, alpha, beta, state))

            if pruningValue < alpha: return pruningValue
            beta = min(beta, pruningValue)

        return pruningValue


    def alphaMinimaxRecursive(self, agent, depth, alpha, beta, gameState: GameState):
        if depth == self.depth or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)
        
        pruningValue = -math.inf

        nextAgent = (agent + 1) % gameState.getNumAgents()
        if nextAgent == 0: depth += 1
        recursive = self.alphaMinimaxRecursive if nextAgent == 0 else self.betaMinimaxRecursive

        actions = gameState.getLegalActions(agent)
        for action in actions:
            state = gameState.generateSuccessor(agent, action)
            pruningValue = max(pruningValue, recursive(nextAgent, depth, alpha, beta, state))

            if pruningValue > beta: return pruningValue
            alpha = max(alpha, pruningValue)

        return pruningValue


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
    Your expectimax agent (question 4)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        actions = gameState.getLegalActions(0)
        scores = [self.expectimaxRecursive(1, 0, gameState.generateSuccessor(0, action)) for action in actions]

        return actions[scores.index(max(scores))]

    def expectimaxRecursive(self, agent, depth, gameState: GameState):
        if depth == self.depth or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)

        nextAgent = (agent + 1) % gameState.getNumAgents()
        if nextAgent == 0: depth += 1

        actions = gameState.getLegalActions(agent)
        successors = [gameState.generateSuccessor(agent, action) for action in actions]
        scores = [self.expectimaxRecursive(nextAgent, depth, state) for state in successors]

        return max(scores) if agent == 0 else sum(map(lambda score: (1 / len(scores)) * score, scores))


def betterEvaluationFunction(currentGameState: GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"

    # Helpers
    position = currentGameState.getPacmanPosition()
    foodCount = currentGameState.getNumFood();
    ghostStates = currentGameState.getGhostStates()

    # Calculation of evaluation
    evaluation = currentGameState.getScore()
    evaluation += 100 / (foodCount + 0.1)

    ghostDistances = [manhattanDistance(position, ghost.getPosition()) for ghost in ghostStates if ghost.scaredTimer == 0]
    ghostDistance = min(ghostDistances) if len(ghostDistances) != 0 else 0
    evaluation += 100 / (ghostDistance + 0.5)

    return evaluation


# Abbreviation
better = betterEvaluationFunction
