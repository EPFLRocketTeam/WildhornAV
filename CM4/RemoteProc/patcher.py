import patch

pset = patch.fromfile("update.patch")

pset.apply(1)
