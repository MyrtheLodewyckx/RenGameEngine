I wanted my engine to be as user friendly as possible.
Therefore I used a statemachine to take care of the gamestates.
That way it is very easy to add and remove the scenes.

Plenty of managers take care of things like input, audio, events...

For the events I used a system where the oldest one in the queue gets 
deleted every frame. That's gives everything the change to deal with 
it at their own time, without having to worry about if the event 
should be deleted or is another class still needs it.