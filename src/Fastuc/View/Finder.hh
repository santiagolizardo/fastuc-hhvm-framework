<?hh // strict
namespace Fastuc\View;

class Finder
{
	/**
	 * @var array
	 */
	private array<string> $searchPaths;

	/**
	 * @var array
	 */
	private array<string> $cachedPaths;

	public function __construct()
	{
		$this->searchPaths = array( '.' );
		$this->cachedPaths = array();
	}

	/**
	 * @param string $path
	 */
	public function addPath( string $path ) : void
	{
		$this->searchPaths[] = $path;
	}

	/**
	 * Replaces the current search path array with a new one.
	 *
	 * @param array $paths
	 */
	public function setPaths( array<string> $paths ) : void
	{
		$this->searchPaths = $paths;
	}

	/**
	 * @return array
	 */
	public function getPaths() : array<string>
	{
		return $this->searchPaths;
	}

	/**
	 * @throws \Fastuc\View\Exception if the view was not found on any search path.
	 * @param string $name
	 * @return string
	 */
	public function find( string $name )
	{
		if( isset( $this->cachedPaths[ $name ] ) )
		{
			return $this->cachedPaths[ $name ];
		}

		foreach( $this->searchPaths as $path )
		{
			$fullPath = $path . DIRECTORY_SEPARATOR . $name . '.php';
			if( file_exists( $fullPath ) )
			{
				$this->cachedPaths[ $name ] = $fullPath;
				return $fullPath;
			}
		}

		throw new \Fastuc\View\Exception( "Template '$name' not found." );
	}
}
