#include "Tutorial.h"

void CoWorkTutorial()
{
	/// .`CoWork`
	
	/// `CoWork` is intented to be use when thread are used to speedup code by distributing tasks
	/// over multiple CPU cores. `CoWork` spans a single set of worker threads that exist for the
	/// whole duration of program run. `CoWork` instances then manage assigning jobs to these
	/// worker threads and waiting for the all work to finish.
	
	/// Job units to `CoWork` are represented by `Function<void ()>` and thus can be written
	/// inline as lambdas.
	
	/// As an example, following code reads input file by lines, splits lines into words (this
	/// is the parallelized work) and then adds resulting words to `Index`:

	FileIn in(GetDataFile("test.txt")); // let us open some tutorial testing data
	
	Index<String> w;
	Mutex m; // need mutex to serialize access to w

	CoWork co;
	while(!in.IsEof()) {
		String ln = in.GetLine();
		co & [ln, &w, &m] {
			Vector<String> h = Split(ln, [](int c) { return IsAlpha(c) ? 0 : c; });
			Mutex::Lock __(m);
			for(const auto& s : h)
				w.FindAdd(s);
		};
	}
	co.Finish();
	
	DUMP(w);
	
	/// Adding words to `w` requires `Mutex`. Alternative to this 'result gathering' `Mutex` is
	/// CoWork::FinLock. The idea behind this is that CoWork requires an internal `Mutex` to
	/// serialize access to common data, so why `FinLock` locks this internal mutex a bit
	/// earlier, saving CPU cycles required to lock and unlock dedicated mutex. From API
	/// contract perspective, you can consider `FinLock` to serialize code till the end of
	/// worker job.

	in.Seek(0);
	while(!in.IsEof()) {
		String ln = in.GetLine();
		co & [ln, &w, &m] {
			Vector<String> h = Split(ln, [](int c) { return IsAlpha(c) ? 0 : c; });
			CoWork::FinLock(); // replaces the mutex, locked till the end of CoWork job
			for(const auto& s : h)
				w.FindAdd(s);
		};
	}
	co.Finish();

	DUMP(w);
	
	/// Of course, the code performed after FinLock should not take long, otherwise there is
	/// negative impact on all CoWork instances. In fact, from this perspective, above code is
	/// probably past this threshold...
}
