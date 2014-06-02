<?hh // strict

/**
 * Updates the include path with the main classes directory.
 */
$includePath = get_include_path();
$srcDirPath = dirname( __DIR__ ) . DIRECTORY_SEPARATOR . 'src';
set_include_path( $includePath . PATH_SEPARATOR . $srcDirPath );

if( !defined( 'CONFIG_PATH' ) ) define( 'CONFIG_PATH', __DIR__ . DIRECTORY_SEPARATOR . 'config' );

function autoloader4phpunit( $className )
{
	$path = dirname( __DIR__ ) . DIRECTORY_SEPARATOR . 'src' . DIRECTORY_SEPARATOR . str_replace( '\\', DIRECTORY_SEPARATOR, $className ) . '.hh';
	if( file_exists( $path ) )
	{
		require $path;
	}
}

spl_autoload_register( 'autoloader4phpunit' );

