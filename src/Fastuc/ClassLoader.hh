<?hh // strict
namespace Fastuc;

class ClassLoaderException extends \Exception {}

/**
 * Manage all the lifecycle of classes, instantiation, destruction and other
 * peculiarities such as if a class it's singleton or not.
 */
class ClassLoader
{
	const DEFAULT_FILE_EXTENSION = '.hh';

	/**
	 * @var ClassLoader
	 */
	private static \Fastuc\ClassLoader $singleton = null;

	/**
	 * Returns the only existing instance of this class.
	 *
	 * @return ClassLoader
	 */
	public static final function getInstance() : this
	{
		if( null === self::$singleton )
		{
			self::$singleton = new self;
		}

		return self::$singleton;
	}

	private Map<string, mixed> $singletons;

	private Vector<string> $inclusionPaths;

	/**
	 * Constructor is not available for a singleton class.
	 */
	private function __construct()
	{
		$this->singletons = new Map<string, mixed>;
		$this->inclusionPaths = Vector<string> {  __DIR__ };

		spl_autoload_register( [ $this, 'loadFile' ] );
	}

	/**
	 * @param string $inclusionPath
	 */
	public function addInclusionPath( string $inclusionPath ) : void
	{
		$this->inclusionPaths->add( $inclusionPath );
	}

	/**
	 * @param string $className
	 */
	public function loadFile( string $className ) : void
	{
		$className = trim( $className, '\\' );
		$classNameForPath = $className;
		if( false !== strpos( $className, '\\' ) )
		{
			$classNameForPath = str_replace( '\\', '_', $className );
		}
		$path = DIRECTORY_SEPARATOR . str_replace( '_', DIRECTORY_SEPARATOR, $classNameForPath ) . self::DEFAULT_FILE_EXTENSION;

		foreach( $this->inclusionPaths as $incPath )
		{
			$fullPath = $incPath . $path;
			if( file_exists( $fullPath ) && is_file( $fullPath ) )
			{
				require_once $fullPath;
				return;
			}
		}

		// @TODO throw new ClassLoaderException( 'Classname not found: ' . $className );
	}

	/**
	 * Returns a new instance of the class passed as first argument.
	 *
	 * @param string $className Class name. (not fully qualified)
	 * @param array $args Optional list of arguments to use during instantiation.
	 * @return object
	 */
	public function newInstance( string $className, array $args = array() ) : mixed
	{
		if( false === class_exists( $className ) )
		{
			$this->loadFile( $className );
		}

		try
		{
			$instance = new \ReflectionClass( $className );
			return $instance->newInstanceArgs( $args );
		}
		catch( \ReflectionException $re )
		{
			throw new ClassLoaderException( $re->getMessage() );
		}
	}

	/**
	 * @param string $className
	 * @param array $args
	 */
	public function newSingleton( string $className, array $args = array() ) : mixed
	{
		if( $this->singletons->containsKey( $className ) )
		{
			return $this->singletons[ $className ];
		}

		return ( $this->singletons[ $className ] = $this->newInstance( $className, $args ) );
	}
}

