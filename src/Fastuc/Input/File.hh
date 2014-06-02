<?hh // strict
namespace Fastuc\Input;

class File
{
	/**
	 * @var array
	 */
	private array $input;

	/**
	 * @param string $name
	 */
	public function __construct( string $name )
	{
		if( false === isset( $_FILES[ $name ] ) )
		{
			throw new Exception( 'Invalid file name: ' . $name );
		}
		
		$this->input = $_FILES[ $name ];
	}

	/**
	 * @param integer $index
	 * @return bool
	 */
	public function hasErrors( int $index = null ) : bool
	{
		if( null !== $index )
		{
			$error = $this->input['error'][ $index ];
		}
		else
		{
			$error = $this->input['error'];
		}

		return ( UPLOAD_ERR_OK !== $error );
	}

	/**
	 * @param integer $index
	 * @return string The mime type of the file, if the browser provided this information.
	 */
	public function getContentType( int $index = null ) : string
	{
		return null !== $index? $this->input['type'][$index]: $this->input['type'];
	}
	
	/**
	 * @param integer $index
	 * @return int The error code associated with this file upload. This element was added in PHP 4.2.0
	 */
	public function getErrorCode( int $index = null ) : int
	{
		return null !== $index? $this->input['error'][$index]: $this->input['error'];
	}

	/**
	 * @param integer $index
	 * @return string The original name of the file on the client machine.
	 */
	public function getName( int $index = null ) : string
	{
		return null !== $index? $this->input['name'][$index]: $this->input['name'];
	}

	/**
	 * @param integer $index
	 * @return int The size, in bytes, of the uploaded file.
	 */
	public function getSize( int $index = null ) : int
	{
		return null !== $index? $this->input['size'][$index]: $this->input['size'];
	}

	/**
	 * @param integer $index
	 * @return string The temporary filename of the file in which the uploaded file was stored on the server.
	 */
	public function getFilename( int $index = null ) : string
	{
		return null !== $index? $this->input['tmp_name'][$index]: $this->input['tmp_name'];
	}
}

