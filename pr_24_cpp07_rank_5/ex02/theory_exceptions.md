Feature                Java                                            C++
----------------------------------------------------------------------------------------
Exception type          throws (checked) in method signature;       No declaration needed
declaration             optional for unchecked

Checked vs unchecked    Checked exceptions must be declared or      All exceptions are unchecked; compiler
                        caught; unchecked are optional             does not enforce

Throwing                throw new ExceptionType();                  throw ExceptionType();

Catching                try { } catch (ExceptionType e) { }        try { } catch (ExceptionType& e) { }

Finally / Cleanup       finally { } always executes                 No finally; use RAII (destructors) or try/catch

Unhandled exception     JVM prints stack trace, program stops       Terminates program, may call std::terminate()
