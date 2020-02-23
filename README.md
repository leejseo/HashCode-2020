# HashCode-2020
Contains some of our team's for Qual Round of Google Hash Code 2020.

## F. Libraries of the world: 5,316,305

Let's call an order of libraries/books as a state.
Define distance d(S, T) between two states (S, T) as minimum number of swap (includes both swapping pair of books/libraries)
to obtain T from S.

Our solution starts from some random/greedy states. Then,  
For 300,000 times:
- Search for a new random "near" state
- If new state is better than current state
  - current state := new state

This simple solution gave us 5,316,305 points.
