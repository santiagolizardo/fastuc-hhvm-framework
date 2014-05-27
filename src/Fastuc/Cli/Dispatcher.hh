<?hh // strict
namespace Fastuc\Cli;

class Dispatcher
{
	/**
	 * @param array $argv
	 * @param string $route
	 */
	public function dispatch( array $argv, string $route ) : void
	{
		$className = '\\App\\Cli\\Controller\\' . ucfirst( $route );
		if( class_exists( $className ) == false )
		{
			$this->terminate( 1, 'Invalid route: ' . $route );
		}

		try
		{
			$controller = new $className;
			if( !( $controller instanceof \Fastuc\Controller\Cli ) )
			{
				$this->terminate( 1, 'Invalid controller: ' . $className );
			}

			$controller->main( $argv );

			$this->terminate( 0 );
		}
		catch( \Exception $e )
		{
			$this->terminate( 1, $e->getMessage() );
		}
	}

	/**
	 * @param string $code
	 * @param string $message
	 */
	public function terminate( string $code, string $message = null ) : void
	{
		if( !empty( $message ) )
		{
			echo $message, PHP_EOL;
		}
		exit( $code );
	}
}

