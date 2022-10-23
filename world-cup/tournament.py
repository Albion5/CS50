# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    # sys.argv[1] is the name of csv file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        # For each line in the csv file
        for row in reader:
            # Create a dictionary with keys "team" and "rating" and add to them values
            team = {}
            team["team"] = row["team"]
            team["rating"] = int(row["rating"])
            # Add team dictionary to the teams list
            teams.append(team)
    # Create a dictionary where the keys are teams and the values are the number of times when the team has won the tournament
    counts = {}
    # Add to the dictionary each team key with the value 0
    for team_dict in teams:
        name = team_dict["team"]
        counts[name] = 0
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)
        # Use winner as the key in counts dict and update the number of times the team has won
        counts[winner] += 1
        # The second way to do the same
        # This way lines 33-35 and 40 can be deleted or commented
        # if winner in counts:
        #     counts[winner] += 1
        # else:
        #     counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []
    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # Simulate rounds untill there's only one winner in teams list
    while len(teams) != 1:
        teams = simulate_round(teams)
    winner = teams[0]["team"]
    return winner


if __name__ == "__main__":
    main()
