<?hh // strict
namespace Fastuc\Utils;

/**
 * Launches command line programs safely.
 */
class CommandLineExecutor
{
	/**
	 * @var string
	 */
	private string $programName;

	private Vector<string> $arguments;

	/**
	 * @var string
	 */
	private string $output;

	/**
	 * @var integer
	 */
	private int $exitCode;

	/**
	 * @param string $programName
	 */
	public function __construct( string $programName )
	{
		$this->programName = $programName;
		$this->arguments = new Vector<string>();
	}

	/**
	 * @param string $arg
	 */
	public function addArgument( string $arg ) : void
	{
		$this->arguments[] = escapeshellarg( $arg );
	}

	/**
	 * @return string
	 */
	public function run() : string
	{
		$parts = array_merge( (array)$this->programName, $this->arguments->toArray() );
		$command = implode( ' ', $parts );
		return exec( $command, $this->output, $this->exitCode );
	}

	/**
	 * @return string
	 */
	public function getOutput() : string
	{
		return implode( PHP_EOL, $this->output );
	}

	/**
	 * @return integer
	 */
	public function getExitCode() : int
	{
		return $this->exitCode;
	}
}

