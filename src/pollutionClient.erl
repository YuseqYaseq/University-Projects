%%%-------------------------------------------------------------------
%%% @author Joseph
%%% @copyright (C) 2018, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 10. May 2018 15:09
%%%-------------------------------------------------------------------
-module(pollutionClient).
-author("Joseph").

%% API
-export([start/0, stop/0, loop/0]).

loop() ->
  %%server ! {self(), addStation, [{1,1}, "Krakow"]},
  receive
    X ->
      io:fwrite("~p~n", [X]),
      loop()
  end.

start() ->
  register(client, spawn(pollutionClient, loop, [] )).

stop() ->
  unregister(client).